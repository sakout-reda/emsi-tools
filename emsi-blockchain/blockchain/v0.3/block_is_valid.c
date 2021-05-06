#include "blockchain.h"

/**
 * validate_tx - validates each tx
 * @node: tx
 * @idx: index of node
 * @arg: visitor
 * Return: 0 if continue else 1
 */
int validate_tx(llist_node_t node, unsigned int idx, void *arg)
{
	transaction_t *tx = node;
	validation_vistor_t *visitor = arg;

	if (!idx)
	{
		if (!coinbase_is_valid(tx, visitor->block_index))
			visitor->valid = 0;
	}
	else if (!transaction_is_valid(tx, visitor->all_unspent))
	{
		dprintf(2, "validate_tx: invalid idx %u\n", idx);
		visitor->valid = 0;
	}
	return (0);
}

/**
 * block_is_valid - verify that a block is valid
 *
 * @block: pointer to the block to be verified
 * @prev_block: pointer to the previous block (or NULL if @block is the first)
 * @all_unspent: list of all unspent transaction outputs
 *
 * Return: If the block is invalid, return 1.
 * Otherwise, return 0.
 */
int block_is_valid(
	block_t const *block, block_t const *prev_block, llist_t *all_unspent)
{
	uint8_t hash_buf[SHA256_DIGEST_LENGTH] = {0};
	block_t const _genesis = BLOCK_GENESIS_INIT;
	validation_vistor_t visitor = {0};

	if (!block || (!prev_block && block->info.index != 0))
		return (1);
	if (block->info.index == 0)
		return (memcmp(block, &_genesis, sizeof(_genesis)));
	if (block->info.index != prev_block->info.index + 1)
		return (1);
	if (!block_hash(prev_block, hash_buf) ||
		memcmp(hash_buf, prev_block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (memcmp(prev_block->hash, block->info.prev_hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (!block_hash(block, hash_buf) ||
		memcmp(hash_buf, block->hash, SHA256_DIGEST_LENGTH))
		return (1);
	if (block->data.len > BLOCK_DATA_MAX_LEN)
		return (1);
	if (!hash_matches_difficulty(block->hash, block->info.difficulty))
		return (1);
	if (llist_size(block->transactions) < 1)
		return (1);
	visitor.valid = 1;
	visitor.all_unspent = all_unspent;
	visitor.block_index = block->info.index;
	if (llist_for_each(block->transactions, validate_tx, &visitor) ||
		!visitor.valid)
		return (1);
	return (0);
}

