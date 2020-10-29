// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("兽兽[2;37;0m[2;37;0m", ({"lxd"}));        
        set("gender", "男性");                
        set("long", "小猫咪~~喵~喵~~小猫咪~~喵~喵~~小猫咪~~喵~喵~~小猫咪~~喵~喵~~[2;37;0m
它是断兵的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lxdong");
        set("owner_name", "断兵");
        set_temp("owner", "lxdong");
        set_temp("owner_name", "断兵");
        ::setup();
}
