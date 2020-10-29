// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m雪山飞狐[2;37;0m[2;37;0m", ({"fox"}));        
        set("gender", "女性");                
        set("long", "小狐狸XD[2;37;0m
它是天石的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kido");
        set("owner_name", "天石");
        set_temp("owner", "kido");
        set_temp("owner_name", "天石");
        ::setup();
}
