// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m彩虹[2;37;0m[2;37;0m", ({"mrch"}));        
        set("gender", "女性");                
        set("long", "一道$HIM$彩虹。[2;37;0m
它是慕容晓星的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mrong");
        set("owner_name", "慕容晓星");
        set_temp("owner", "mrong");
        set_temp("owner_name", "慕容晓星");
        ::setup();
}
