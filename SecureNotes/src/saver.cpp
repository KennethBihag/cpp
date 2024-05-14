#include "saver.h"

#include <iostream>

using namespace std;

namespace secure_notes
{
    void Saver::show()
    {
        for(map<string,string>::iterator i = m_site_pass_dict.begin();
			i != m_site_pass_dict.end(); ++i)
        {
			
			cout << "Original: " << i->first << ' ' << i->second << endl;
			string encrypted = i->second;
			for(int i = 0; i < encrypted.length(); i++)
			{
				encrypted[i] = encrypted[i]+1;
			}
			cout << "\tNew: " << encrypted << endl;	
        }
    }
}; // namespace secure_notes