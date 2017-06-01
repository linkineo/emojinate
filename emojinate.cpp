#include <iostream>
#include <string>

const uint32_t base_smiley = 0xf09f9881;

void decode(std::string val)
{

        int v = 0;
        std::string out = "";
        for(int p=0;p<val.length()/4;p++)
        {

                uint8_t vals[4];

                vals[0] = val[v+0];
                vals[1] = val[v+1];
                vals[2] = val[v+2];
                vals[3] = val[v+3];

                v=v+4;

                uint32_t code = (vals[0] << 24) + (vals[1] << 16) + (vals[2] << 8) + vals[3];
                //std::cout << "RES=" << std::hex << (uint32_t)code << std::endl;
                //std::cout << "CHAR=" <<  (char)((uint32_t)(base_smiley) - 1 - code + 'Z') << std::endl;
                
                out.push_back((char)((uint32_t)(base_smiley) - 1 - code + 'Z'));;
        }

        std::cout << "Decoded --> " << out << std::endl;
}

std::string encode(std::string outval)
{
        std::string outp ="";


        for(int l=0;l<outval.length();l++)
        {
                uint8_t alpha = 'Z' - 1 - (uint8_t)outval[l];
                outp.push_back((uint8_t)(base_smiley >> 24));
                outp.push_back((uint8_t)(base_smiley >> 16));
                outp.push_back((uint8_t)(base_smiley >> 8));
                outp.push_back((uint8_t)(base_smiley & 0xFF)+alpha);
        }
        std::cout << "Encoded --> =" << outp << std::endl;
        return outp;

}

int main(int argc, char** argv)
{

        if(argc > 2)
        {
          std::string arg(argv[1]);
          if(arg == "d")
          {
            std::string val(argv[2]);
            decode(val);
          }

          if(arg == "e")
          {
            std::string val(argv[2]);
            encode(val);
          }

        }else
        {
          std::cout << "Usage:" << std::endl;
          std::cout << "Encode (only [A-Z] upper case right now): [app] e text" << std::endl;
          std::cout << "Decode: [app] d emojis" << std::endl;
          std::cout << "Example: 😊😙😆😈😑😗😏  = PATRICK" << std::endl;
        }

        return 0;
}
