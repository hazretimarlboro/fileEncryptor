````markdown
# XOR File Encryptor/Decryptor

A simple C program set to **encrypt and decrypt files** using a repeating-key XOR cipher.  

> ⚠️ **Security Notice:** This implementation is **not secure for sensitive data**. Repeating-key XOR is vulnerable to attacks if the key is shorter than the file or reused. Use for learning or non-critical files only.

---

## Features

- Encrypt any file using a user-provided encoder string.
- Decrypt files encrypted with the corresponding encoder string.
- Processes files in chunks for efficiency with large files.

---

## Files

- `encryptor.c` – encrypts a file using a XOR cipher with a user-provided encoder string.
- `decryptor.c` – decrypts a previously encrypted file using the same encoder string.
- `README.md` – this file.

---

## Compilation

Use `gcc` or any C compiler:

```bash
gcc encryptor.c -o encryptor
gcc decryptor.c -o decryptor
````

This will produce executables `encryptor` and `decryptor`.

---

## Usage

### Encrypt a file

```bash
./encryptor <filename>
```

1. Enter the encoder string when prompted (max 128 characters).
2. The encrypted file will be saved as `encrypted` in the current directory.

Example:

```bash
./encryptor mydocument.txt
Please enter the encoder string:
mysecretkey
```

---

### Decrypt a file

```bash
./decryptor <encrypted_filename>
```

1. Enter the same encoder string that was used for encryption.
2. The decrypted file will be saved as `decrypted` in the current directory.

Example:

```bash
./decryptor encrypted
Enter encoder string: 
mysecretkey
```

---

## How it works

1. Reads the input file in **chunks** of 4096 bytes.
2. XORs each byte with the corresponding byte of the encoder string, repeated as necessary.
3. Writes the result to the output file.

> Encryption and decryption are symmetric: running the same XOR process twice with the same key restores the original file.

---

## Limitations

* Encoder string repeats if the file is longer than the key.
* Vulnerable to **known-plaintext and frequency analysis attacks**.
* Only suitable for **educational purposes** or **low-security file obfuscation**.

---

## License

This project is released under the MIT License. Use freely, but **do not rely on it for strong security**.

```

---