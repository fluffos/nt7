// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m起司喵喵[2;37;0m[2;37;0m", ({"cheese"}));        
        set("gender", "女性");                
        set("long", "这是一只绿茶婊，后来被抓来给人骑了[2;37;0m
它是天幻的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kennyg");
        set("owner_name", "天幻");
        set_temp("owner", "kennyg");
        set_temp("owner_name", "天幻");
        ::setup();
}
