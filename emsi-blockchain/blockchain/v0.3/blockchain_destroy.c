#include "blockchain.h"

/**
 * blockchain_destroy - destroy a blockchain
 *
 * @blockchain: pointer to the blockchain
 */
void blockchain_destroy(blockchain_t *blockchain)
{
	if (blockchain)
	{
		if (blockchain->chain)
			llist_destroy(blockchain->chain, 1,
				(node_dtor_t)block_destroy);
		blockchain->chain = NULL;
		if (blockchain->unspent)
			llist_destroy(blockchain->unspent, 1, free);
		blockchain->unspent = NULL;
		free(blockchain);
	}
}
