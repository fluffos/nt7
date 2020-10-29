// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m欧西里斯[2;37;0m[2;37;0m", ({"osiris"}));        
        set("gender", "男性");                
        set("long", "天空龙[2;37;0m
它是北宫凡的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dqw");
        set("owner_name", "北宫凡");
        set_temp("owner", "dqw");
        set_temp("owner_name", "北宫凡");
        ::setup();
}
