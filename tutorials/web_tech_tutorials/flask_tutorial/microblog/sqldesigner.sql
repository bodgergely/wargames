-- WWW SQL Designer
-- ---
-- Globals
-- ---
-- SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
-- SET FOREIGN_KEY_CHECKS=0;
-- ---
-- Table 'users'
-- user table
-- ---
DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `username` VARCHAR(64) NULL DEFAULT NULL,
  `email` VARCHAR(120) NULL DEFAULT NULL,
  `password_hash` VARCHAR(128) NOT NULL DEFAULT 'NULL',
  PRIMARY KEY (`id`),
  KEY (`username`),
  KEY (`email`),
  UNIQUE KEY (`username`),
  UNIQUE KEY (`email`)
) COMMENT 'user table';
-- ---
-- Table 'posts'
--
-- ---
DROP TABLE IF EXISTS `posts`;
CREATE TABLE `posts` (
  `id` INTEGER NULL AUTO_INCREMENT DEFAULT NULL,
  `body` VARCHAR(140) NULL DEFAULT NULL,
  `timestamp` DATETIME NULL DEFAULT NULL,
  `user_id` INTEGER NULL DEFAULT NULL,
  PRIMARY KEY (`id`)
);
-- ---
-- Foreign Keys
-- ---
ALTER TABLE `posts`
ADD
  FOREIGN KEY (user_id) REFERENCES `users` (`id`);
-- ---
  -- Table Properties
  -- ---
  -- ALTER TABLE `users` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
  -- ALTER TABLE `posts` ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;
  -- ---
  -- Test Data
  -- ---
  -- INSERT INTO `users` (`id`,`username`,`email`,`password_hash`) VALUES
  -- ('','','','');
  -- INSERT INTO `posts` (`id`,`body`,`timestamp`,`user_id`) VALUES
  -- ('','','','');