#include <iostream>
using namespace std;

int main(){
    cout << R"(
 /$$       /$$   /$$ /$$   /$$  /$$$$$$   /$$$$$$  /$$$$$$$$ /$$      
| $$      | $$  | $$| $$  /$$/ /$$__  $$ /$$__  $$|__  $$__/| $$      
| $$      | $$  | $$| $$ /$$/ | $$  \__/| $$  \__/   | $$   | $$      
| $$      | $$  | $$| $$$$$/  |  $$$$$$ | $$         | $$   | $$      
| $$      | $$  | $$| $$  $$   \____  $$| $$         | $$   | $$      
| $$      | $$  | $$| $$\  $$  /$$  \ $$| $$    $$   | $$   | $$      
| $$$$$$$$|  $$$$$$/| $$ \  $$|  $$$$$$/|  $$$$$$/   | $$   | $$$$$$$$
|________/ \______/ |__/  \__/ \______/  \______/    |__/   |________/
    )";
  string name;
  int choice;
  string encrypt_name;

  do{

    cout << "\n\nSelect the options";

    cout << "\n1. See the filesystem";
    cout << "\n2. Select the filesystem";
    cout << "\n3. Encrypt the filesystem";
    cout << "\n4. Open the filesystem";
    cout << "\n5. Close the filesystem";
    cout << "\n6. Delete the filesystem";
    cout << "\n7. Exit\n";
    cout << "\nEnter your choice: ";
    cin >> choice;

    if(choice == 1){
      system("lsblk");
      cout << "\n";
    }

    else if(choice == 2){
      cout << "\nEnter the name of the filesystem you want to select (simple name, dont use /dev): ";
      cin >> name;
      cout << "\n";
    }

    else if(choice == 3){

      if (name.empty()) {
        cout << "No filesystem selected.\n";
        continue;
      }

      char choice_temp;
      cout << "\nDo you really want to Encrypt " << name << " (y or n): ";
      cin >> choice_temp;

      if (choice_temp == 'y'){
        cout << "\nEncrypting...";
        string temp_cmd = "sudo cryptsetup luksFormat /dev/";
        string cmd = temp_cmd + name;

        system(cmd.c_str());
      }
    }

    else if(choice == 4){

      cout <<"\nWhat should be the encrypted filesystem should be called (any name without spaces): ";
      cin >> encrypt_name;

      cout << "\nJust enter the password you used to encrypt below";

      string temp_cmd = "sudo cryptsetup open /dev/";
      string temp_cmd1 = temp_cmd + name;
      string final_cmd = temp_cmd1 + " " + encrypt_name;

      system(final_cmd.c_str());

      cout << "\nDo you want to initialize the filesystem(Only first time, data will be lost)(y or n): ";

      char temp_choice;

      cin >> temp_choice;

      if(temp_choice == 'y'){
        int mkfs_choice;
        cout << "\nSelect which one do you want to use: ";
        cout << "\n1. ext4 (default)";
        cout << "\n2. exfat";
        cout << "\n3. btrfs\n";
        cout << ": ";
        cin >> mkfs_choice;
        string mkfs_cmd;

        cout << "\n";
        if(mkfs_choice == 1){
          string temp_mkfs = "sudo mkfs.ext4 /dev/mapper/";
          mkfs_cmd = temp_mkfs + encrypt_name;

          system(mkfs_cmd.c_str());
        }

        else if(mkfs_choice == 2){
          string temp_mkfs = "sudo mkfs.exfat /dev/mapper/";
          mkfs_cmd = temp_mkfs + encrypt_name;

          system(mkfs_cmd.c_str());
        }

        else if(mkfs_choice == 3){
          string temp_mkfs = "sudo mkfs.btrfs /dev/mapper/";
          mkfs_cmd = temp_mkfs + encrypt_name;

          system (mkfs_cmd.c_str());
        }

        else{
          cout <<"\nError";
          return 0;
        }
      }
    }

    else if (choice == 5){
      string temp = "sudo cryptsetup close ";
      string temp_cmd = temp + encrypt_name;
      system(temp_cmd.c_str());
      cout << "\nSuccess";
    }

    else if (choice == 6){
      string temp = "sudo wipefs -a /dev/";
      string temp_cmd = temp + name;
      system(temp_cmd.c_str());
      cout << "\nSuccess";
    }
    else{
      cout << "\n";
    }
  }while(choice!=7);

  cout << "\nGoodbye\n";
}

