# passworEncrypter
A C password-encrypter implementation, designed to be used via CLI. It uses two flags, -e and -d in order to encrypt, and decrypt respectively

# How it works 
## (top level explanation)
Basically, it uses dev/urandom Linux file to select a random shift for Caesar cipher encrypting.
Since it uses this file, it is mathematically impossible to discover the actual password from the encrypted text.


## Demo version
Since you may want to use some CLI special characters or the answer may contain them, you will have to use single quotes ('') in order to send what you want to encrypt/decrypt

### Encrypting
```
$./encrypter -e 'hello_fellas**123'
Encrypting...
d{^xEXex2B"B4M^xCV/B\z`lKBKByiSBiW
come back later :D
$
```
### Decrypting
```
$./encrypter -d  '{^xEXex2B"B4M^xCV/B\z`lKBKByiSBiW'
Decrypting...
hello_fellas**123
Thanks, come back later :D
$
```
# Main Goal
My main goal is to allow anyone to keep a plain text file with all their passwords **securely**

# My Recommendation
I really recommend (since we are executing this in the wonderful Linux environment) to change owner and execution permission of the executable itself **AND** your password file.

# How to compile
Compile it as any other C file:
gcc new_sofi.c encrypter