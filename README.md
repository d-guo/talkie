# talkie
Implementation of the Regev PKE Scheme based on the Learning with Errors problem, which is believed to be secure against post-quantum attacks.

## Details
Communication is implemented with a TCP server and a TCP client, such that the client can send messages to the server securely, so even if a message is intercepted by an adversary, the adversary cannot decipher it.

## Use / Experimentation
Run the server and client in different terminals. The client-side will be asked to give an input, and the server will output the given input from the client. The intermediary ciphertext is generated and can be saved to disk with slight modification.

## PKE Scheme
The server runs the setup to generate the public and secret keys, and it sends the public key to the client. The client then encrypts its messages with the public and sends the ciphertexts (encryptions) to the server. The server then decrypts them with the secret key to obtain the messages.