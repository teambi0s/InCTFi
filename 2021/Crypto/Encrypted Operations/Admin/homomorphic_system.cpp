#include <cstdlib>
#include <palisade.h>

using namespace lbcrypto;

class homomorphic_system
{

public:
  int plaintextMod;
  double sigma;
  uint32_t depth;

  SecurityLevel securityLevel;

  Ciphertext<DCRTPoly> ciphertext;
  Ciphertext<DCRTPoly> moddedct;

  //################################################################################################

  homomorphic_system()
  {

    plaintextMod = 65537;
    sigma = 3.2;
    securityLevel = HEStd_128_classic;
    depth = 2;
  }

  //################################################################################################

  CryptoContext<DCRTPoly> genCC()
  {

    CryptoContext<DCRTPoly> cryptoContext =
        CryptoContextFactory<DCRTPoly>::genCryptoContextBFVrns(
            plaintextMod, securityLevel, sigma, 0, depth, 0, OPTIMIZED);

    cryptoContext->Enable(ENCRYPTION);
    cryptoContext->Enable(SHE);

    return cryptoContext;
  }

  //################################################################################################

  LPKeyPair<DCRTPoly> genKeys(CryptoContext<DCRTPoly> cryptoContext)
  {

    LPKeyPair<DCRTPoly> keyPair;

    keyPair = cryptoContext->KeyGen();

    cryptoContext->EvalMultKeyGen(keyPair.secretKey);

    cryptoContext->EvalAtIndexKeyGen(keyPair.secretKey, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19});

    return keyPair;
  }

  //################################################################################################

  Ciphertext<DCRTPoly> genCiphertexts(vector<int64_t> msgvector, LPKeyPair<DCRTPoly> keyPair, CryptoContext<DCRTPoly> cryptoContext)
  {

    Plaintext plaintext = cryptoContext->MakePackedPlaintext(msgvector);
    ciphertext = cryptoContext->Encrypt(keyPair.publicKey, plaintext);

    return ciphertext;
  }

  //################################################################################################

  void compute(CryptoContext<DCRTPoly> cryptoContext, char operation, int samt = 1, vector<int64_t> operandVector = {0})
  {

    Plaintext ov = cryptoContext->MakePackedPlaintext(operandVector);

    if (operation == '+')
    {
      moddedct = cryptoContext->EvalAdd(ciphertext, ov);
      ciphertext = moddedct;
    }

    else if (operation == '*')
    {
      moddedct = cryptoContext->EvalMult(ciphertext, ov);
      ciphertext = moddedct;
    }

    // left shift '+' right shift '-'
    else if (operation == '>')
    {
      moddedct = cryptoContext->EvalAtIndex(ciphertext, -samt);
      ciphertext = moddedct;
    }

    else if (operation == '<')
    {
      moddedct = cryptoContext->EvalAtIndex(ciphertext, samt);
      ciphertext = moddedct;
    }

    else
    {
      std::cout << "\n\nERROR!! "
                << "Unrecognized Operation!!\n"
                << operation;
      exit(0);
    }
  }

  //################################################################################################

  vector<int64_t> decrypt(LPKeyPair<DCRTPoly> keyPair, CryptoContext<DCRTPoly> cryptoContext)
  {

    LPPrivateKey<DCRTPoly> sk;

    sk = keyPair.secretKey;

    Plaintext plaintextResult;
    cryptoContext->Decrypt(sk, moddedct, &plaintextResult);

    vector<int64_t> pt = plaintextResult->GetPackedValue();

    return pt;
  }
};

// for better understanding of how the above class is used
// if u have installed pallisade use the below code to test the above class implementation

//################################################################################################
//########################################## MAIN() ##############################################

// int main() {

//   vector<int64_t> msgvector = {1,2,3,4,5,6,7,8,9,10};
//   vector<int64_t> operandVector = {-1,-2,3,4,5,6,7,8,10,9};

//   char operation = '+';
//   int samt = 1;

//   homomorphic_system obj;

//   CryptoContext<DCRTPoly> cryptoContext = obj.genCC();
//   LPKeyPair<DCRTPoly> keyPair = obj.genKeys(cryptoContext);
//   obj.genCiphertexts(msgvector, keyPair, cryptoContext);
//   obj.copmute(, cryptoContext, operation, samt, operandVector);

//   std::cout << "\n\nResults of homomorphic computations" << std::endl;
//   std::cout << "\nct + ov: " <<  obj.decrypt(keyPair, cryptoContext) << std::endl;

//   return 0;
// }

//#################################------------------------------####################################
//################################--------------------------------###################################
