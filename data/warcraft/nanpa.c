// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m麒麟神主[2;37;0m[2;37;0m", ({"kirin"}));        
        set("gender", "女性");                
        set("long", "传说中的超机人[2;37;0m
它是黄兴孙文的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nanpa");
        set("owner_name", "黄兴孙文");
        set_temp("owner", "nanpa");
        set_temp("owner_name", "黄兴孙文");
        ::setup();
}
