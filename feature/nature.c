// nature.c
// by Find.
// 此特性标准 room 和 npc 里已经继承，
// 区域编程可以直接引用这些函数。

// 这个函数返回当前游戏的年度数.
int query_year()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_year();
}

/* 这个函数返回当前游戏的季节.
 * 返回值 "1" : 春季.
 * 返回值 "2" : 夏季.
 * 返回值 "3" : 秋季.
 * 返回值 "4" : 冬季.
 */
int query_season()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_season();
}

// 这个函数返回当前游戏的月份数(1 - 12).
int query_month()
{

        int month,day;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( NATURE_D->query_month(),"month %d:day %d",month,day);

        return month;
}

// 这个函数返回现在是此月中的第几天。
int query_day_in_month()
{
        int month,day;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( NATURE_D->query_month(),"month %d:day %d",month,day);

        return day;
}

// 这个函数返回当前处于一年中的第几天(1 - 365).
int query_day(int *month_day)
{
        object ob = find_object(NATURE_D);

        if(!ob) error("error: Can't find NATURE_D.\n");

        return ob->query_day(month_day);
}

// 这个函数返回当前的天气状况.
// 目前的状况有: clear 晴,snow 雪,wind 风,fog 雾,cloudy 云,
// cloudy 进展到最后就是雨.
string weather_now()
{
        string effect,degree;

        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->query_weather(),"%s %s",effect,degree);

        return effect;
}

// 这个函数返回当前的天气状况进展的程度.
// "begain" : 刚刚开始,不明显.
// "last"   : 开始加重了.
// "finish" : 非常严重,但也进展到最后了.
// 比如 "cloudy" 如果进展到 "finish" 就要下雨了.
// "clear" 的程度没有意义.就返回一个 "now".
// 如果您所要做的效果需要精确的采集到当前的天气状况.
// 就需要结合状况、程度和季节综合的判断。
string weather_degree()
{
        string effect,degree;

        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->query_weather(),"%s %s",effect,degree);

        return degree;

}

// 这个函数判断目前是白天还是黑夜.
// 返回值为 "1" : 白天.
// 返回值为 "0" : 黑夜.
int is_day()
{
        string day_night;
        int time;
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        sscanf( ob->day_or_night(),"%s %d",day_night,time);

        return (day_night == "day");
}

// 这个函数返回昼夜更替的一些详细信息.
// 返回值是一个字串,格式为: "day_or_night last_time".
// day_or_night 为一个字串,值为 "day" 或者 "night" 反
// 映目前是白天还是黑夜.
// last_time 是一个 int,反映的是距离昼夜更替所剩的时间.
// 比如返回值 "day 280" 说明目前是白天,距离夜晚还有280秒.
// 中间以一个空格隔开.
string day_night()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->day_or_night();
}

// 这个函数返回目前为一天中的第几分钟.
int query_time()
{
        object ob = find_object(NATURE_D);

        if(!ob) write("error: Can't find NATURE_D.\n");

        return ob->query_current_time();
}