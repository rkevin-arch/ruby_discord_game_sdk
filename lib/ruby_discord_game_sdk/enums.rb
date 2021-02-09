# frozen_string_literal: true

module DiscordGameSDK
  module Result
    Ok = 0
    ServiceUnavailable = 1
    InvalidVersion = 2
    LockFailed = 3
    InternalError = 4
    InvalidPayload = 5
    InvalidCommand = 6
    InvalidPermissions = 7
    NotFetched = 8
    NotFound = 9
    Conflict = 10
    InvalidSecret = 11
    InvalidJoinSecret = 12
    NoEligibleActivity = 13
    InvalidInvite = 14
    NotAuthenticated = 15
    InvalidAccessToken = 16
    ApplicationMismatch = 17
    InvalidDataUrl = 18
    InvalidBase64 = 19
    NotFiltered = 20
    LobbyFull = 21
    InvalidLobbySecret = 22
    InvalidFilename = 23
    InvalidFileSize = 24
    InvalidEntitlement = 25
    NotInstalled = 26
    NotRunning = 27
    InsufficientBuffer = 28
    PurchaseCanceled = 29
    InvalidGuild = 30
    InvalidEvent = 31
    InvalidChannel = 32
    InvalidOrigin = 33
    RateLimited = 34
    OAuth2Error = 35
    SelectChannelTimeout = 36
    GetGuildTimeout = 37
    SelectVoiceForceRequired = 38
    CaptureShortcutAlreadyListening = 39
    UnauthorizedForAchievement = 40
    InvalidGiftCode = 41
    PurchaseError = 42
    TransactionAborted = 43
  end

  module CreateFlags
    Default = 0
    NoRequireDiscord = 1
  end

  module LogLevel
    Error = 1
    Warn = 2
    Info = 3
    Debug = 4
  end

  module UserFlag
    Partner = 2
    HypeSquadEvents = 4
    HypeSquadHouse1 = 64
    HypeSquadHouse2 = 128
    HypeSquadHouse3 = 256
  end

  module PremiumType
    None = 0
    Tier1 = 1
    Tier2 = 2
  end

  module ImageType
    User = 0
  end

  module ActivityType
    Playing = 0
    Streaming = 1
    Listening = 2
    Watching = 3
  end

  module ActivityActionType
    Join = 1
    Spectate = 2
  end

  module ActivityJoinRequestReply
    No = 0
    Yes = 1
    Ignore = 2
  end

  module Status
    Offline = 0
    Online = 1
    Idle = 2
    DoNotDisturb = 3
  end

  module RelationshipType
    None = 0
    Friend = 1
    Blocked = 2
    PendingIncoming = 3
    PendingOutgoing = 4
    Implicit = 5
  end
  module LobbyType
    Private = 1
    Public = 2
  end

  module LobbySearchComparison
    LessThanOrEqual = -2
    LessThan = -1
    Equal = 0
    GreaterThan = 1
    GreaterThanOrEqual = 2
    NotEqual = 3
  end

  module LobbySearchCast
    String = 1
    Number = 2
  end

  module LobbySearchDistance
    Local = 1
    Default = 2
    Extended = 3
    Global = 4
  end

  module EntitlementType
    Purchase = 1
    PremiumSubscription = 2
    DeveloperGift = 3
    TestModePurchase = 4
    FreePurchase = 5
    UserGift = 6
    PremiumPurchase = 7
  end

  module SkuType
    Application = 1
    DLC = 2
    Consumable = 3
    Bundle = 4
  end

  module InputModeType
    VoiceActivity = 0
    PushToTalk = 1
  end
end
