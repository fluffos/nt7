#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/xuanfengtui");

object get_owner()
{
    object owner;
    if(objectp(book)) {
        owner = environment(book);
        if(owner->is_character()) return owner;
    }
    return 0;
}

object book_owner = get_owner();
nosave string book_owner_name=(objectp(book_owner) && userp(book_owner))?query("name", book_owner):"某人";

int do_rumor(string arg)
{
    CHANNEL_D->do_channel(this_object(), "rumor", arg);
    return 1;
}

int get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    do_rumor("听说" + book_owner_name + "精神失常，旋风扫叶腿法被扔进了路边的垃圾箱！");
    return 1;
}

nosave mixed *story = ({
        "黄药师：蓉儿，近来江湖中出现了许多人偷学我桃花岛的旋风扫叶腿法，甚是可恨！",
        "黄蓉：很容易啊，我让江湖上提到旋风扫叶腿就怕。",
        (: do_rumor, "江湖传言：东海桃花岛开放，欢迎各路人士前来观光旅游。" :),
        "桃花岛",
        "游客甲：桃花影落飞神剑，碧海潮生按玉箫。",
        "游客乙：果然景色优美！",
        "黄蓉：实乃居家旅游的必来之处。",
        "桃花岛众弟子齐施——旋风扫叶腿！",
        "游客：各位这是在表演节目么？",
        "黄蓉：啊，各位可知，这桃花岛上遍地桃花，一旦开花，地上满是花瓣，打扫起来甚是不易！",
        "黄蓉：为此，我爹爹特意开发了桃花岛专用扫地武学——旋风扫叶腿！",
        "众游客：啊，原来是打扫卫生的。",
        "黄蓉：对！清除垃圾保护环境做一名环保工人的必备武学。",
        "黄药师、众弟子晕倒......",
        "数日后，江湖上",
        "路人甲：看见没，又是个练旋风扫叶腿的。",
        "路人乙：别去管他，那是用来扫地的。",
        "路人丙：扫地也是一份很有前途的职业啊，哪里都需要，不愁下岗啊！",
        book_owner_name + "汗津：旋风扫叶腿＝扫地！！！",
        (: get_book :),
});

string prompt() { return HIW "【武林轶事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
