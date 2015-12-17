module.exports = {
	TOKEN_SECRET: process.env.TOKEN_SECRET || 'JWT Token Secret',
	MONGO_URI: 'mongodb://vipadmin:admin123@vip-dev.cis.fiu.edu:27017/vip',
	//MONGO_URI: 'root:root@localhost:27017/admin',

	//OAuth 2.0
	FOURSQUARE_SECRET: process.env.FOURSQUARE_SECRET || '',
	GOOGLE_SECRET: process.env.GOOGLE_SECRET || 'f6gk-70fxSOu-xzyAM8ceyiD',
	GITHUB_SECRET: process.env.GITHUB_SECRET || '',
	INSTAGRAM_SECRET: process.env.INSTAGRAM_SECRET || '',

	LINKEDIN_SECRET: process.env.LINKEDIN_SECRET || '',
	TWITCH_SECRET: process.env.TWITCH_SECRET || '',
	WINDOWS_LIVE_SECRET: process.env.WINDOWS_LIVE_SECRET || '',
	YAHOO_SECRET: process.env.YAHOO_SECRET || '',

	//OAuth 1.0
	TWITTER_KEY: process.env.TWITTER_KEY || '',
	TWITTER_SECRET: process.env.TWITTER_SECRET || ''
};
