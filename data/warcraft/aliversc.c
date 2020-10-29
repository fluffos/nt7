// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m宫保鸡丁[2;37;0m[2;37;0m", ({"pesia"}));        
        set("gender", "男性");                
        set("long", "宫保鸡丁[2;37;0m
它是阿尔三的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "aliversc");
        set("owner_name", "阿尔三");
        set_temp("owner", "aliversc");
        set_temp("owner_name", "阿尔三");
        ::setup();
}
