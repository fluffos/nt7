// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m藤原纪香[2;37;0m[2;37;0m", ({"mmm"}));        
        set("gender", "女性");                
        set("long", "一名东洋来的美女[2;37;0m
它是风轻扬的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "btong");
        set("owner_name", "风轻扬");
        set_temp("owner", "btong");
        set_temp("owner_name", "风轻扬");
        ::setup();
}
