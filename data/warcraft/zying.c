// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白马[2;37;0m[2;37;0m", ({"zyingg"}));        
        set("gender", "男性");                
        set("long", "$HIW$白马[2;37;0m
它是慕容影的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "zying");
        set("owner_name", "慕容影");
        set_temp("owner", "zying");
        set_temp("owner_name", "慕容影");
        ::setup();
}
