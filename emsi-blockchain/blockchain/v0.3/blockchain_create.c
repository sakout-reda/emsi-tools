#include "blockchain.h"

/**
 * blockchain_create - allocate and initialize a new blockchain
 *
 * Return: If an error occurs, return NULL.
 * Otherwise, return a pointer the the new blockchain.
 */
blockchain_t *blockchain_create(void)
{
	blockchain_t *blockchain = calloc(1, sizeof(*blockchain));
	block_t *block = calloc(1, sizeof(*block));

	if (!blockchain || !block)
	{
		free(blockchain);
		free(block);
		return (NULL);
	}
	blockchain->chain = llist_create(MT_SUPPORT_FALSE);
	blockchain->unspent = llist_create(MT_SUPPORT_FALSE);
	if (!blockchain->chain || !blockchain->unspent)
	{
		free(blockchain);
		free(block);
		return (NULL);
	}
	block->info.index = BLOCK_GENESIS_INIT_INFO_INDEX;
	block->info.difficulty = BLOCK_GENESIS_INIT_INFO_DIFFICULTY;
	block->info.timestamp = BLOCK_GENESIS_INIT_INFO_TIMESTAMP;
	block->info.nonce = BLOCK_GENESIS_INIT_INFO_NONCE;
	memcpy(
		block->info.prev_hash,
		BLOCK_GENESIS_INIT_INFO_PREV_HASH, SHA256_DIGEST_LENGTH);
	memcpy(
		block->data.buffer,
		BLOCK_GENESIS_INIT_DATA_BUFFER, BLOCK_GENESIS_INIT_DATA_LEN);
	block->data.len = BLOCK_GENESIS_INIT_DATA_LEN;
	memcpy(
		block->hash,
		BLOCK_GENESIS_INIT_HASH, SHA256_DIGEST_LENGTH);
	if (llist_add_node(blockchain->chain, block, ADD_NODE_FRONT) == -1)
	{
		llist_destroy(blockchain->chain, 1, NULL);
		free(blockchain);
		free(block);
		return (NULL);
	}
	return (blockchain);
}
