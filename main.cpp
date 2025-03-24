#include "splendor.hpp"

using namespace std;

signed main () {
  int mode = MODE_EXIT;

  system("CHCP 65001");
  
  while ((mode = menu())) {
    main_game(mode);
  }
  return 0;
}
