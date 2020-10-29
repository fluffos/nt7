inherit SKILL;
void create() { seteuid(getuid()); }
string type() { return "knowledge"; }
int practice_skill(object me)
{   
        return notify_fail("炼丹术只能通过学习(learn)，或者在实践中提高!\n");
}