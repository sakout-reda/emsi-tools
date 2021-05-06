#include "blockchain.h"

/**
 * hash_tx_ids - llist action func to hash outputs
 * @node: transaction_t* struct
 * @idx: index of node
 * @arg: pointer to address to write to
 * Return: Always 0
 */
static int hash_tx_ids(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	memcpy(*(uint8_t **)arg, ((transaction_t *)node)->id, SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;
	return (0);
}

/**
 * block_hash - compute the hash of a block
 *
 * @block: pointer to the block to be hashed
 * @hash_buf: buffer in which to store the hash of @block
 *
 * Description: If @block is NULL or @hash_buf is NULL, do nothing.
 * Otherwise, compute the hash of the memory area pointed to by @block.
 *
 * Return: If @block is NULL, return NULL.
 * Otherwise, return @hash_buf.
 */
uint8_t *block_hash(
	block_t const *block, uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	size_t len = 0;
	size_t len_init = 0;
	int8_t *buf = NULL;
	int8_t *ptr = NULL;

	if (block && hash_buf)
	{
		len = len_init = sizeof(block->info) + block->data.len;
		if (llist_size(block->transactions) > 0)
			len += llist_size(block->transactions) * SHA256_DIGEST_LENGTH;
		ptr = buf = calloc(1, len);
		if (!buf)
			return (NULL);
		memcpy(ptr, &block->info, len_init);
		ptr += len_init;
		llist_for_each(block->transactions, hash_tx_ids, &ptr);
		sha256(buf, len, hash_buf);
		free(buf);
		return (hash_buf);
	}
	return (NULL);
}
