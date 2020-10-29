// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m杀人螳螂[2;37;0m[2;37;0m", ({"larbs"}));        
        set("gender", "男性");                
        set("long", "我的宠物[2;37;0m
它是发缘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "larb");
        set("owner_name", "发缘");
        set_temp("owner", "larb");
        set_temp("owner_name", "发缘");
        ::setup();
}
