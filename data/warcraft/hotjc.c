// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m七色[2;37;0m[2;37;0m", ({"qiqi"}));        
        set("gender", "男性");                
        set("long", "$HIC$这是一条七色彩龙，小巧可爱。[2;37;0m
它是寒月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hotjc");
        set("owner_name", "寒月");
        set_temp("owner", "hotjc");
        set_temp("owner_name", "寒月");
        ::setup();
}
