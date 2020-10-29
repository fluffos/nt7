// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m嗜血狂狮[2;37;0m[2;37;0m", ({"lauxdbb"}));        
        set("gender", "男性");                
        set("long", "嗜血狂狮[2;37;0m
它是不噬血魔的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "lauxd");
        set("owner_name", "不噬血魔");
        set_temp("owner", "lauxd");
        set_temp("owner_name", "不噬血魔");
        ::setup();
}
