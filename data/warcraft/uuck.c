// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m太古苍龙[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "太古苍龙，盘古开天后第一只神兽，乃万物之源[2;37;0m
它是上官春卷的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "uuck");
        set("owner_name", "上官春卷");
        set_temp("owner", "uuck");
        set_temp("owner_name", "上官春卷");
        ::setup();
}
