// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m玉箫[2;37;0m[2;37;0m", ({"yuxiao"}));        
        set("gender", "男性");                
        set("long", "这是桃花岛镇派之宝——玉箫。[2;37;0m
它是哑奴的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yanu");
        set("owner_name", "哑奴");
        set_temp("owner", "yanu");
        set_temp("owner_name", "哑奴");
        ::setup();
}
