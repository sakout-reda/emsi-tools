#include "transaction.h"

/**
 * transaction_hash_input - hash a transaction input
 *
 * @node: transaction input structure
 * @idx: index of list node
 * @arg: address of a pointer to the buffer in which to write
 *
 * Return: Always 0
 */
static int transaction_hash_input(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	tx_in_t *tx_in = node;

	memcpy(*(uint8_t **)arg, tx_in, SHA256_DIGEST_LENGTH * 3);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH * 3;
	return (0);
}

/**
 * transaction_hash_output - hash a transaction output
 *
 * @node: transaction output structure
 * @idx: index of list node
 * @arg: address of a pointer to the buffer in which to write
 *
 * Return: Always 0
 */
static int transaction_hash_output(
	llist_node_t node, unsigned int idx __attribute__((unused)), void *arg)
{
	tx_out_t *tx_out = node;

	memcpy(*(uint8_t **)arg, tx_out->hash, SHA256_DIGEST_LENGTH);
	*(uint8_t **)arg += SHA256_DIGEST_LENGTH;
	return (0);
}

/**
 * transaction_hash - compute the ID (hash) of a transaction
 *
 * @transaction: pointer to the transaction of which to compute the hash
 * @hash_buf: address of a buffer in which to store the computed hash
 *
 * Return: If transaction is NULL or memory allocation fails, return NULL.
 * Otherwise, return @hash_buf.
 */
uint8_t *transaction_hash(
	transaction_t const *transaction,
	uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	ssize_t len = 0;
	uint8_t *buf = NULL;
	uint8_t *ptr = NULL;

	if (!transaction)
		return (NULL);
	len = SHA256_DIGEST_LENGTH * 3 * llist_size(transaction->inputs)
		+ SHA256_DIGEST_LENGTH * llist_size(transaction->outputs);
	buf = ptr = calloc(1, len);
	if (!buf)
		return (NULL);
	llist_for_each(transaction->inputs, transaction_hash_input, &ptr);
	llist_for_each(transaction->outputs, transaction_hash_output, &ptr);
	if (!sha256((const int8_t *)buf, len, hash_buf))
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	return (hash_buf);
}
