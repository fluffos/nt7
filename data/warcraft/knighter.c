// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m黄金虎[2;37;0m[2;37;0m", ({"goldentiger"}));        
        set("gender", "男性");                
        set("long", "据说是高处不胜寒和老虎杂交的品种。[2;37;0m
它是汉军铁骑的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "knighter");
        set("owner_name", "汉军铁骑");
        set_temp("owner", "knighter");
        set_temp("owner_name", "汉军铁骑");
        ::setup();
}
