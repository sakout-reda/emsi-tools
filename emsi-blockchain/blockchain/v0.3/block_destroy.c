#include "blockchain.h"

/**
 * block_destroy - destroy a block
 *
 * @block: pointer to the block to destroy
 */
void block_destroy(block_t *block)
{
	if (block)
	{
		llist_destroy(block->transactions, 1,
			(node_dtor_t)transaction_destroy);
		block->info.index = 0;
		block->info.difficulty = 0;
		block->info.timestamp = 0;
		block->info.nonce = 0;
		memset(block->info.prev_hash, 0, SHA256_DIGEST_LENGTH);
		memset(block->data.buffer, 0, BLOCK_DATA_MAX_LEN);
		block->data.len = 0;
		memset(block->hash, 0, SHA256_DIGEST_LENGTH);
		free(block);
	}
}
