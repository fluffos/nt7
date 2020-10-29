// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("王牌神兽[2;37;0m[2;37;0m", ({"acerxw"}));        
        set("gender", "男性");                
        set("long", "流风之回雪之神兽[2;37;0m
它是流风回雪的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "lfhx");
        set("owner_name", "流风回雪");
        set_temp("owner", "lfhx");
        set_temp("owner_name", "流风回雪");
        ::setup();
}
