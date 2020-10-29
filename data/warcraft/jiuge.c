// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m菩提树[2;37;0m[2;37;0m", ({"puti"}));        
        set("gender", "男性");                
        set("long", "这是佛主种下的一株菩提树。[2;37;0m
它是九哥的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "jiuge");
        set("owner_name", "九哥");
        set_temp("owner", "jiuge");
        set_temp("owner_name", "九哥");
        ::setup();
}
