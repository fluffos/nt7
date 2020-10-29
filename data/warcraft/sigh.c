// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m雷夔[2;37;0m[2;37;0m", ({"thunder_"}));        
        set("gender", "男性");                
        set("long", "其形状如牛，形巨大，独脚撑天，闪耀如日月般的光芒和声若雷霆！[2;37;0m
它是一生叹息的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sigh");
        set("owner_name", "一生叹息");
        set_temp("owner", "sigh");
        set_temp("owner_name", "一生叹息");
        ::setup();
}
