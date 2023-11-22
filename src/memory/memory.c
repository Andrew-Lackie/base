#include <m_stdlib.h>
#include <memory.h>
#include <logger.h>
#include <asserts.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <signal.h>

static const char* memory_tag_strings[MEMORY_TAG_MAX_TAGS] = {
    "UNKNOWN    ",
    "ARRAY      ",
    "VECTOR     ",
    "MATRIX     ",
    "LINEAR_ALLC",
    "THREADS    ",
    "STRING     ",
    "HASHTABLE  "};

struct memory_stats {
    u64 total_allocated;
    u64 tagged_allocations[MEMORY_TAG_MAX_TAGS];
};

static struct memory_stats stats;

void initialize_memory()
{
    memset(&stats, 0, sizeof(stats));
}

static void memset_aligned(void *block, char byte, size_t n_bytes)
{
    M_ASSERT_MSG((n_bytes & 0x0F) == 0, "n_bytes & 0X00F != 0");
    M_ASSERT_MSG(((uintptr_t)block & 0x0F) == 0, "(unintptr)block & 0x0F is not 0");
    memset(block, byte, n_bytes);
}

void* m_allocate(size_t size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_allocate called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }
    if (size == 0) {
        LOG_WARN("m_allocate size parameter is 0. Returning NULL");
        return NULL;
    }
    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    void *block = malloc(size);
    memset(block, 0, size);

    return block;
}

void* m_reallocate(void* block, size_t size, memory_tag tag)
{
    void* new_block;

    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_rallocate called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }
    if (size == 0) {
        LOG_WARN("m_rallocate size parameter is 0. Returning NULL");
        return NULL;
    }

    if (block == NULL) {
        LOG_WARN("Memory size is NULL. Creating new allocation.");
        new_block = m_allocate(size, tag);
    }
    else {
        stats.total_allocated -= sizeof(block);
        stats.total_allocated += size;
        stats.tagged_allocations[tag] -= sizeof(block);
        stats.tagged_allocations[tag] += size;

        new_block = realloc(block, size);
        memset(new_block, 0, size);
    }
    return new_block;
}

void* m_allocate_aligned(size_t size, memory_tag tag, size_t alignment)
{
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_allocate_aligned called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }
    if (size == 0) {
        LOG_WARN("m_allocate_aligned size parameter is 0. Returning NULL");
        return NULL;
    }
    stats.total_allocated += size;
    stats.tagged_allocations[tag] += size;

    uintptr_t mask = ~(uintptr_t)(alignment - 1);
    void *block = malloc(size + alignment - 1);
    void *ptr = (void *)(((uintptr_t)block + alignment - 1) & mask);
    assert((alignment & (alignment - 1)) == 0);

    memset_aligned(ptr, 0, size);

    printf("0x%08" PRIXPTR ", 0x%08" PRIXPTR "\n", (uintptr_t)block, (uintptr_t)ptr);

    free(block);

    return ptr;
}

void m_free(void* block, size_t size, memory_tag tag)
{
    if (tag == MEMORY_TAG_UNKNOWN) {
        LOG_WARN("m_free called using MEMORY_TAG_UNKNOWN. Re-class this allocation");
    }

    stats.total_allocated -= size;
    stats.tagged_allocations[tag] -= size;

    free(block);
}

void* m_copy_memory(void* dest, const void* source, size_t size)
{
    return memcpy(dest, source, size);
}

void* m_set_memory(void* dest, i32 value, size_t size)
{
    return memset(dest, value, size);
}

char* get_memory_usage_str()
{
    char buffer[8000] = "System memory use (tagged):\n";
    u64 offset = strlen(buffer);
    for (u32 i = 0; i < MEMORY_TAG_MAX_TAGS; i++) {
        char unit[4] = "XiB";
        f32 amount = 1.0f;
        if (stats.tagged_allocations[i] >= (f32)GIBIBYTES(1)) {
            unit[0] = 'G';
            amount = stats.tagged_allocations[i] / (f32)GIBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= MEBIBYTES(1)) {
            unit[0] = 'M';
            amount = stats.tagged_allocations[i] / (f32)MEBIBYTES(1);
        }
        else if (stats.tagged_allocations[i] >= (f32)KIBIBYTES(1)) {
            unit[0] = 'K';
            amount = stats.tagged_allocations[i] / (f32)KIBIBYTES(1);
        }
        else {
            unit[0] = 'B';
            unit[1] = 0;
            amount = (f32)stats.tagged_allocations[i];
        }

        i32 length = snprintf(buffer + offset, 8000, " %s: %.2f%s\n", memory_tag_strings[i], amount, unit);
        offset += length;
    }
    char* out_string = m_strdup(buffer);
    return out_string;
}
