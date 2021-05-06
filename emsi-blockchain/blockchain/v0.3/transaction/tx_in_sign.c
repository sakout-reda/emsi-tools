#include "transaction.h"

/**
 * tx_in_sign - sign a transaction input
 *
 * @in: pointer to the transaction input structure to sign
 * @tx_id: buffer containing the ID of the transaction in which @in is stored
 * @sender: buffer containing the private key of the receiver of the coins in
 *          the transaction output referenced by the transaction input
 * @all_unspent: list of all unspent transaction outputs
 *
 * Return: If an error occurs, return NULL.
 * Otherwise, return a pointer to the resulting signature.
 */
sig_t *tx_in_sign(
	tx_in_t *in, uint8_t const tx_id[SHA256_DIGEST_LENGTH],
	EC_KEY const *sender, llist_t *all_unspent)
{
	uint8_t pub[EC_PUB_LEN] = {0};
	ssize_t index = 0;
	unspent_tx_out_t *unspent_tx_out = NULL;
	int all_unspent_count = llist_size(all_unspent);

	if (all_unspent_count == -1)
		return (NULL);

	while (index < all_unspent_count)
	{
		unspent_tx_out = llist_get_node_at(all_unspent, index);
		if (!memcmp(in->tx_out_hash, unspent_tx_out->out.hash,
				SHA256_DIGEST_LENGTH))
		{
			break;
		}
		unspent_tx_out = NULL;
		index += 1;
	}

	if (!unspent_tx_out)
		return (NULL);
	if (!ec_to_pub(sender, pub))
		return (NULL);
	if (memcmp(pub, unspent_tx_out->out.pub, EC_PUB_LEN))
		return (NULL);
	if (!ec_sign(sender, tx_id, SHA256_DIGEST_LENGTH, &in->sig))
		return (NULL);

	return (&in->sig);
}
