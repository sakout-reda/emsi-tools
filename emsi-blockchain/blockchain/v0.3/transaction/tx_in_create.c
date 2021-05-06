#include "transaction.h"

/**
 * tx_in_create - create a transaction input
 *
 * @unspent: pointer to unspent transaction output to use as a an input
 *
 * Return: If memory allocation fails, return NULL.
 * Otherwise, return a pointer to the new transaction input structure.
 */
tx_in_t *tx_in_create(unspent_tx_out_t const *unspent)
{
	tx_in_t *tx_in = NULL;

	if (!unspent)
		return (NULL);
	tx_in = calloc(1, sizeof(*tx_in));
	if (!tx_in)
		return (NULL);
	memcpy(tx_in->block_hash, unspent->block_hash,
		sizeof(tx_in->block_hash));
	memcpy(tx_in->tx_id, unspent->tx_id,
		sizeof(tx_in->tx_id));
	memcpy(tx_in->tx_out_hash, unspent->out.hash,
		sizeof(tx_in->tx_out_hash));
	return (tx_in);
}
