// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m哈雷摩托[2;37;0m[2;37;0m", ({"halei"}));        
        set("gender", "男性");                
        set("long", "哈雷摩托车[2;37;0m
它是美国队长的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "talkssss");
        set("owner_name", "美国队长");
        set_temp("owner", "talkssss");
        set_temp("owner_name", "美国队长");
        ::setup();
}
