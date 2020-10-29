// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m阿布[2;37;0m[2;37;0m", ({"abu"}));        
        set("gender", "男性");                
        set("long", "阿布是一头上古传说中的神龙。[2;37;0m
它是慕容复燕的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jiuyong");
        set("owner_name", "慕容复燕");
        set_temp("owner", "jiuyong");
        set_temp("owner_name", "慕容复燕");
        ::setup();
}
