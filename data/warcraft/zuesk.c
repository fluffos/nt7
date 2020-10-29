// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33;43m叶黄[2;37;0m[2;37;0m", ({"zuesks"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是黄叶的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zuesk");
        set("owner_name", "黄叶");
        set_temp("owner", "zuesk");
        set_temp("owner_name", "黄叶");
        ::setup();
}
