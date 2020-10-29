// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m大雪龙骑[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "大雪龙骑[2;37;0m
它是红衣的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "avred");
        set("owner_name", "红衣");
        set_temp("owner", "avred");
        set_temp("owner_name", "红衣");
        ::setup();
}
