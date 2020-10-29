// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("哈哈[2;37;0m[2;37;0m", ({"hahah"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是火魔的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "rumeng");
        set("owner_name", "火魔");
        set_temp("owner", "rumeng");
        set_temp("owner_name", "火魔");
        ::setup();
}
