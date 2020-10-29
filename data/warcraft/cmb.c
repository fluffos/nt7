// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m秋风落叶[2;37;0m[2;37;0m", ({"icmb"}));        
        set("gender", "女性");                
        set("long", "神雕[2;37;0m
它是慕容秋的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cmb");
        set("owner_name", "慕容秋");
        set_temp("owner", "cmb");
        set_temp("owner_name", "慕容秋");
        ::setup();
}
