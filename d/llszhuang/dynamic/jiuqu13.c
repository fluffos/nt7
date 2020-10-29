inherit ROOM;
void create()
{
        set("short", "七曲九回廊");
        set("long",
"这里是七、八十道长廊，相互接连，连绵不绝，直是无穷无尽。每个\n"
"长廊转弯处都有一盏宛如鬼火般摇晃不定的黄灯。廊边的潭水在灯光照射\n"
"下发出墨绿的异光。\n"
);
        set("no_magic", "1");

        setup();
}
int valid_leave(object me, string dir)
{
     if( random(query("kar", me))>27){
     message_vision("只听地板吱呀呀几声想后，地板突然翻了起来，$N一下掉了进去。\n", me);
     me->move("/d/llszhuang/didao");
     return notify_fail("");}
     return ::valid_leave(me, dir);
}
