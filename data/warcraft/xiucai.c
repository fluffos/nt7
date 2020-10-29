// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("踏[1;37m雪[1;34m乌锥[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹马全身乌黑亮丽，宛如锦缎，无一根杂色，龙吟虎步。[2;37;0m
它是吕秀才的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiucai");
        set("owner_name", "吕秀才");
        set_temp("owner", "xiucai");
        set_temp("owner_name", "吕秀才");
        ::setup();
}
