// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m踏雪乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身乌黑亮丽，无一根杂色，宛如锦缎，龙声虎步。[2;37;0m
它是李大嘴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dazui");
        set("owner_name", "李大嘴");
        set_temp("owner", "dazui");
        set_temp("owner_name", "李大嘴");
        ::setup();
}
