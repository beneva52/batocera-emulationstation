#pragma once

#include <vector>
#include <string>
#include "FileData.h"
#include "Window.h"
#include "MetaData.h"
#include "PlatformId.h"
#include "ThemeData.h"

class SystemData
{
public:
	SystemData(std::string name, std::string fullName, std::string startPath,
                               std::vector<std::string> extensions, std::string command,
                               std::vector<PlatformIds::PlatformId> platformIds, std::string themeFolder,
                               std::map<std::string, std::vector<std::string>*>* map);
	SystemData(std::string name, std::string fullName, std::string command,
			   std::string themeFolder, std::vector<SystemData*>* systems);
	~SystemData();

	inline FileData* getRootFolder() const { return mRootFolder; };
	inline const std::string& getName() const { return mName; }
	inline const std::string& getFullName() const { return mFullName; }
	inline const std::string& getStartPath() const { return mStartPath; }
	inline const std::vector<std::string>& getExtensions() const { return mSearchExtensions; }
	inline const std::string& getThemeFolder() const { return mThemeFolder; }
	inline bool getHasFavorites() const { return mHasFavorites; }
	inline bool isFavorite() const { return mIsFavorite; }
	inline std::vector<FileData*> getFavorites() const { return mRootFolder->getFavoritesRecursive(GAME); }

	inline const std::vector<PlatformIds::PlatformId>& getPlatformIds() const { return mPlatformIds; }
	inline bool hasPlatformId(PlatformIds::PlatformId id) { return std::find(mPlatformIds.begin(), mPlatformIds.end(), id) != mPlatformIds.end(); }

	inline const std::shared_ptr<ThemeData>& getTheme() const { return mTheme; }

	std::string getGamelistPath(bool forWrite) const;
	bool hasGamelist() const;
	std::string getThemePath() const;
	
	unsigned int getGameCount() const;
	unsigned int getFavoritesCount() const;
	unsigned int getHiddenCount() const;

	void launchGame(Window* window, FileData* game);

	static void deleteSystems();
	static bool loadConfig(); //Load the system config file at getConfigPath(). Returns true if no errors were encountered. An example will be written if the file doesn't exist.
	static void writeExampleConfig(const std::string& path);
	static std::string getConfigPath(bool forWrite); // if forWrite, will only return ~/.emulationstation/es_systems.cfg, never /etc/emulationstation/es_systems.cfg

	static std::vector<SystemData*> sSystemVector;
	static SystemData *getFavoriteSystem();

	inline std::vector<SystemData*>::const_iterator getIterator() const { return std::find(sSystemVector.begin(), sSystemVector.end(), this); };
	inline std::vector<SystemData*>::const_reverse_iterator getRevIterator() const { return std::find(sSystemVector.rbegin(), sSystemVector.rend(), this); };
	
	inline SystemData* getNext() const
	{
		auto it = getIterator();
		it++;
		if(it == sSystemVector.end()) it = sSystemVector.begin();
		return *it;
	}

	inline SystemData* getPrev() const
	{
		auto it = getRevIterator();
		it++;
		if(it == sSystemVector.rend()) it = sSystemVector.rbegin();
		return *it;
	}

	// Load or re-load theme.
	void loadTheme();
	std::shared_ptr<ThemeData> getloadedTheme();

	// refresh the roms files
	void refreshRootFolder();

	static void reloadSystemsTheme();

	std::map<std::string, std::vector<std::string> *> * getEmulators();
private:
	std::string mName;
	std::string mFullName;
	std::string mStartPath;
	std::vector<std::string> mSearchExtensions;
	std::string mLaunchCommand;
	std::vector<PlatformIds::PlatformId> mPlatformIds;
	std::string mThemeFolder;
	std::shared_ptr<ThemeData> mTheme;

	bool mHasFavorites;
	bool mIsFavorite;

	void populateFolder(FileData* folder);

	FileData* mRootFolder;
	std::map<std::string, std::vector<std::string> *> *mEmulators;
};
