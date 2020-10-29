//禁止使用的中文名字
string *banned_name =
({
"你", "你们", "我", "我们", "他", "他们", "她", "她们", "它", "它们",
"大家", "所有的人", "无", "某人",
"创始人", "系统", "核心", "系统核心", "系统管理员", "网管", "管理员",
"毛泽东", "周恩来", "邓小平", "江泽民", "胡锦涛",
"精灵", "频道精灵", "谣言精灵", "战斗精灵",
"天神", "大巫师", "巫师", "巫师学徒",
"女巫", "女巫师", "女天神", "女巫学徒",
"叮当", "布丁", "行客儿", "阿兰", "阿飞",
});

//禁止注册的ID
string *banned_id =
({
"chat", "new", "rumor", "tell", "none", "reply",
"shutdown", "master", "core", "sys", "reboot",
"admin", "wizard", "arch",
"dick", "shit", "cao", "cunt", "slut", "damn",
"tnnd", "fuck", "fuckyou",
"dugu", "bubai", "all", "yuan", "chen", "chuanfu",
"east","west","south","north","enter","out",
"southeast","southwest","northeast","northwest",
"eastup", "eastdown", "westup", "westdown",
"southup", "southdown", "northup", "northdown", "corpse",
});

//被purge后仍在申诉期内的id
string *purge_id =
({
});

//开放多个登录id的ip
string *bar_ip =
({
"202.98.13.2",//吉林一大学校园网
"61.132.182.2",//一学校代理
"218.104.54.7"//点击网吧
});
