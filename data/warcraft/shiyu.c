// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m乌云[5m[1;37m闪电驹[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这匹西域神驹通体雪白，追风逐电、龙行虎步，神骏非常。[2;37;0m
它是方世玉的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shiyu");
        set("owner_name", "方世玉");
        set_temp("owner", "shiyu");
        set_temp("owner_name", "方世玉");
        ::setup();
}
