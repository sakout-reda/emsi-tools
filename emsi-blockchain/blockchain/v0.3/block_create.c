#include "blockchain.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * block_create - allocate and initialize a block
 *
 * @prev: pointer to the previous block in the blockchain
 * @data: pointer to the start of the memory area to duplicate
 * @data_len: number of bytes to duplicate in @data
 *
 * Description: If @data_len is greater than BLOCK_DATA_MAX_LEN, only
 * BLOCK_DATA_MAX_LEN bytes will be duplicated into the block's data buffer.
 * The block’s index will be one plus the previous block’s index.
 * The block’s difficulty and nonce will both be initialized to zero.
 * The block’s timestamp will be initialized using the time(2) system call.
 * The block’s hash buffer will be zero-initialized.
 *
 * Return: If an error occurs, return NULL.
 * Otherwise, return a pointer to the new block.
 */
block_t *block_create(
	block_t const *prev, int8_t const *data, uint32_t data_len)
{
	block_t *block = NULL;
	llist_t *transactions = NULL;

	if (!prev || !data)
	{
		return (NULL);
	}
	block = calloc(1, sizeof(*block));
	if (!block)
	{
		return (NULL);
	}
	transactions = llist_create(MT_SUPPORT_FALSE);
	if (!transactions)
	{
		free(block);
		return (NULL);
	}
	block->info.index = prev->info.index + 1;
	block->info.difficulty = 0;
	block->info.timestamp = time(NULL);
	block->info.nonce = 0;
	memcpy(block->info.prev_hash, prev->hash, SHA256_DIGEST_LENGTH);
	block->data.len = MIN(data_len, BLOCK_DATA_MAX_LEN);
	memcpy(block->data.buffer, data, block->data.len);
	block->transactions = transactions;
	return (block);
}
