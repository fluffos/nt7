// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihu"}));        
        set("gender", "男性");                
        set("long", "普通坐骑[2;37;0m
它是小号的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xiaohao");
        set("owner_name", "小号");
        set_temp("owner", "xiaohao");
        set_temp("owner_name", "小号");
        ::setup();
}
