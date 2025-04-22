import React, { createContext, useContext, useState } from 'react';

const BlogContext = createContext();

export const useBlogContext = () => useContext(BlogContext);

export const BlogProvider = ({ children }) => {
  const [isDarkMode, setIsDarkMode] = useState(false);

  const toggleDarkMode = () => {
    setIsDarkMode((prevMode) => !prevMode);
  };

  return (
    <BlogContext.Provider value={{ isDarkMode, toggleDarkMode }}>
      {children}
    </BlogContext.Provider>
  );
};
