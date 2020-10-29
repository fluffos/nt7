// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m燕云铁骑[2;37;0m[2;37;0m[2;37;0m", ({"yanyun"}));        
        set("gender", "女性");                
        set("long", "燕云18铁骑，踏平一切奸侫[2;37;0m
它是萧峰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaofeng");
        set("owner_name", "萧峰");
        set_temp("owner", "xiaofeng");
        set_temp("owner_name", "萧峰");
        ::setup();
}
