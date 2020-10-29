// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m遗忘[2;37;0m[2;37;0m", ({"mao"}));        
        set("gender", "男性");                
        set("long", "一缕轻风，一壶清茶，伴随着同样又一个思念她的日和夜[2;37;0m
它是过去的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "cod");
        set("owner_name", "过去");
        set_temp("owner", "cod");
        set_temp("owner_name", "过去");
        ::setup();
}
